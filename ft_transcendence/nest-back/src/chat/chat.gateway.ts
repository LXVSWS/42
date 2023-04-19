import { OnGatewayConnection, OnGatewayDisconnect, SubscribeMessage, WebSocketGateway, WebSocketServer } from "@nestjs/websockets";
import { Server, Socket } from "socket.io";
import { UsersService } from "src/users/users.service";
import { ChatRoom } from "./chatRooms";

@WebSocketGateway({ namespace: 'chat', cors: { origin: "*" } })
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
	@WebSocketServer() server: Server;

	constructor(
		private usersService: UsersService
	) { }

	private ChatRooms: ChatRoom[] = [];

	async handleConnection(client: Socket) {
		const user = await this.usersService.getByUsername(client.handshake.auth.username)
		if (user) {
			client.data.userId = user.id;
		}
	}

	handleDisconnect(client: Socket) {

	}

	@SubscribeMessage('banUser')
	async handleMute(client: Socket, info: string) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]))
		const user = await this.usersService.getByUsername(info[1]);
		if (room && user) {
			this.handleKickUser(client, info);
			room.ban(user.id);
			setTimeout(() => {
				room.unban(user.id);
			}, 10000);
		}
	}

	@SubscribeMessage('kickUser')
	async handleKickUser(client: Socket, info: string) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]));
		const user = await this.usersService.getByUsername(info[1]);
		if (room && user) {
			room.deleteUser(user.id);
			this.sendConnectedUsers(info[0], room);
			this.server.to(info[0]).emit('kicked', info[1]);
		}
	}

	@SubscribeMessage('muteUser')
	async handleMuteUser(client: Socket, info: string) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]));
		const user = await this.usersService.getByUsername(info[1]);
		if (room && user) {
			room.mute(user.id);
			setTimeout(() => {
				room.unmute(user.id);
			}, 10000);
		}
	}

	async sendConnectedUsers(channelId: string, room: ChatRoom) {
		const memberUsername = await Promise.all(room.member.map(async (user) => ((await this.usersService.getProfile(user)).username)));
		const adminUsername = await Promise.all(room.admins.map(async (user) => ((await this.usersService.getProfile(user)).username)));
		this.server.to(channelId).emit('updateConnectedUsers', { member: memberUsername, admin: adminUsername, owner: (await this.usersService.getProfile(room.owner)).username });
	}

	@SubscribeMessage('createRoom')
	async handleRoomCreation(client: Socket, info: string | number) {
		const room = new ChatRoom(client.data.userId, info[0], info[1], info[2], info[3]);
		client.join(room.id);
		this.ChatRooms.push(room);
		this.server.emit('roomUpdate', await this.handleRoom());
		client.emit('joinRoom', room.id);
		return room.id;
	}

	@SubscribeMessage('joinRoom')
	async handleClientJoinRoom(client: Socket, info: string) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]))
		if (room && !room.banList.includes(client.data.userId) && (!room.isProtected || info[1] === room.password || room.member.includes(client.data.userId) || room.admins.includes(client.data.userId) || room.owner === client.data.userId)) {
			client.join(room.id);
			room.addUser(client.data.userId);
			this.sendConnectedUsers(info[0], room);
			this.server.emit('roomUpdate', await this.handleRoom());
			client.emit('joinRoom', room.id);
			return true;
		}
		return false;
	}

	@SubscribeMessage('getRooms')
	async handleRoom() {
		// return only public chatRooms with only the relevant informations
		const rooms = this.ChatRooms.map(({ password, ...rest }) => rest);
		const updatedRooms = await Promise.all(rooms.map(async (room) => {
			const ownerName = (await this.usersService.getProfile(room.owner)).username;
			return { ...room, ownerName }; // Add ownerName property to the room object and return it
		}));
		return updatedRooms;
	}

	@SubscribeMessage('newMessage')
	handleNewMessage(client: Socket, info: string) {
		if (this.ChatRooms.find((room) => ((room.member.includes(client.data.userId) || room.admins.includes(client.data.userId) || room.owner === client.data.userId) && !room.muteList.includes(client.data.userId) && room.id === info[2]))) {
			this.server.to(info[2]).emit('newMessage', info[0], info[1], info[2], info[3]);
		}
	}

	@SubscribeMessage('roomUpdate')
	async handleRoomUpdate(client: Socket, info: string | boolean) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]));
		if (!room)
			return;
		room.update(info[1], info[2]);
		this.server.emit('roomUpdate', await this.handleRoom());
	}

	@SubscribeMessage('getRoomScope')
	returnRoomScore(client: Socket, roomId: string) {
		const room = this.ChatRooms.find((room) => (room.id === roomId))
		if (room)
			return room.isPublic;
		return;
	}

	@SubscribeMessage('leaveRoom')
	async handleQuitRoom(client: Socket, ids: string | number) {
		const room = this.ChatRooms.find((room) => (room.id === ids[0]));
		if (!room)
			return
		room.deleteUser(ids[1]);
		if (room.owner === undefined)
			this.ChatRooms.splice(this.ChatRooms.indexOf(room), 1);
		else {
			this.sendConnectedUsers(ids[0], room);
		}
		this.server.emit('roomUpdate', await this.handleRoom());
	}

	@SubscribeMessage('verifyUser')
	async handleUserVerification(client: Socket, channelId: string) {
		const room = this.ChatRooms.find((room) => (room.id === channelId));
		if (room) {
			const memberUsername = await Promise.all(room.member.map(async (user) => ((await this.usersService.getProfile(user)).username)));
			const adminUsername = await Promise.all(room.admins.map(async (user) => ((await this.usersService.getProfile(user)).username)));
			if (room.member.includes(client.data.userId) || room.admins.includes(client.data.userId) || room.owner === client.data.userId) {
				client.join(channelId);
				return { isConnected: true, isProtected: room.isProtected, roomName: room.name, isAdmin: room.admins.includes(client.data.userId), connectedUser: { member: memberUsername, admin: adminUsername, owner: (await this.usersService.getProfile(room.owner)).username } }
			}
			return { isConnected: false, isProtected: room.isProtected, roomName: room.name, isAdmin: room.admins.includes(client.data.userId), connectedUser: { member: memberUsername, admin: adminUsername, owner: (await this.usersService.getProfile(room.owner)).username } }
		}
		return false;
	}

	@SubscribeMessage('newAdmin')
	async addNewUser(client: Socket, info: any) {
		const room = this.ChatRooms.find((room) => (room.id === info[0]));
		const user = await this.usersService.getByUsername(info[1]);
		if (room && user) {
			room.addAdmin(user.id);
			this.sendConnectedUsers(info[0], room);
		}
	}
}