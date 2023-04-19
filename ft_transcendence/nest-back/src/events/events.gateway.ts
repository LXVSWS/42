import { Logger } from "@nestjs/common";
import { ConnectedSocket, MessageBody, OnGatewayConnection, OnGatewayDisconnect, OnGatewayInit, SubscribeMessage, WebSocketGateway, WebSocketServer } from "@nestjs/websockets";
import { Server, Socket } from "socket.io";

type User = {
	socketId: string,
	username: string,
	isInGame: boolean
}

@WebSocketGateway({
	origin: { cors: "*" },
	namespace: 'events'
})
export class EventsGateway implements OnGatewayConnection, OnGatewayDisconnect {
	private logger = new Logger();

	private connectedUsers: User[] = [];

	@WebSocketServer()
 	server: Server;

	handleConnection(client: Socket) {
		client.data.username = client.handshake.auth.username;
		const index = this.connectedUsers.findIndex(user => user.username === client.data.username);
		this.connectedUsers.push({
			socketId: client.id,
			username: client.data.username,
			isInGame: false
		});
		if (index === -1) {
			this.server.emit("user-connected", client.data.username);
		}
		this.logger.log(client.data.username + " connected");
	}

	handleDisconnect(client: Socket) {
		let index = this.connectedUsers.findIndex(user => user.username === client.data.username);
		if (index !== -1) {
			this.connectedUsers.splice(index, 1);
		}
		index = this.connectedUsers.findIndex(user => user.username === client.data.username);
		if (index === -1) {
			this.server.emit("user-disconnected", client.data.username);
		}
		this.logger.log(client.data.username + " disconnected");
	}

	@SubscribeMessage("send-friend-request")
	handleSendFriendRequest(
		@ConnectedSocket() client: Socket,
		@MessageBody() data: any
	) {
		if (!data || typeof data.id !== "number") {
			return;
		}
		const connectedUserInstances = this.connectedUsers.filter(user => user.username === data.receiverUsername);
		for(let i = 0; i < connectedUserInstances.length; i++) {
			const socketId = connectedUserInstances[i].socketId;
			this.server.to(socketId).emit("receive-friend-request", { id: data.id, creatorUsername: client.data.username });
		}
	}

	@SubscribeMessage("send-game-request")
	handleSendGameRequest(
		@ConnectedSocket() client: Socket,
		@MessageBody() username: string
	) {
		const connectedUserInstances = this.connectedUsers.filter(user => user.username === username);
		for(let i = 0; i < connectedUserInstances.length; i++) {
			const socketId = connectedUserInstances[i].socketId;
			this.server.to(socketId).emit("receive-game-request", client.data.username);
		}
	}

	@SubscribeMessage("remove-friend")
	handleRemoveFriend(
		@ConnectedSocket() client: Socket,
		@MessageBody() username: string
	): void {
		const connectedUserInstances = this.connectedUsers.filter(user => user.username === username);
		for(let i = 0; i < connectedUserInstances.length; i++) {
			const socketId = connectedUserInstances[i].socketId;
			this.server.to(socketId).emit("friend-removed", client.data.username);
		}
	}

	@SubscribeMessage("is-user-connected")
	getUserStatus(@MessageBody() username: string): boolean {
		const index = this.connectedUsers.findIndex(user => user.username === username);
		return (index !== -1);
	}

	@SubscribeMessage("accept-friend-request")
	handleAcceptFriendRequest(
		@ConnectedSocket() client: Socket,
		@MessageBody() username: string
	) {
		const connectedUserInstances = this.connectedUsers.filter(user => user.username === username);
		for(let i = 0; i < connectedUserInstances.length; i++) {
			const socketId = connectedUserInstances[i].socketId;
			this.server.to(socketId).emit("friend-request-accepted", client.data.username);
		}
	}

	@SubscribeMessage("update-username")
	handleUpdateUsername(
		@ConnectedSocket() client: Socket,
		@MessageBody() newUsername: string
	) {
		this.connectedUsers = this.connectedUsers.map(user => {
			if (user.username === client.data.username) {
				user.username = newUsername;
				this.server.to(user.socketId).emit("updated-username", newUsername);
			}
			return user;
		});
		this.server.emit("user-disconnected", client.data.username);
		this.server.emit("user-connected", newUsername);
	}

	@SubscribeMessage("synchronize-username")
	handleSynchronizeUsername(
		@ConnectedSocket() client: Socket,
		@MessageBody() newUsername: string
	) {
		client.data.username = newUsername;
	}

	@SubscribeMessage("join-game")
	handleJoinGame(@ConnectedSocket() client: Socket) {
		this.connectedUsers = this.connectedUsers.map(user => {
			if (user.username === client.data.username) {
				user.isInGame = true;
			}
			return user;
		});
		this.server.emit("user-joined-game", client.data.username);
	}

	@SubscribeMessage("leave-game")
	handleLeaveGame(@ConnectedSocket() client: Socket) {
		this.connectedUsers = this.connectedUsers.map(user => {
			if (user.username === client.data.username) {
				user.isInGame = false;
			}
			return user;
		});
		this.server.emit("user-left-game", client.data.username);
	}

	@SubscribeMessage("is-user-in-game")
	handleIsUserInGame(@MessageBody() username: string) {
		const index = this.connectedUsers.findIndex(user => user.username === username);
		return (index !== -1 && this.connectedUsers[index].isInGame);
	}
}