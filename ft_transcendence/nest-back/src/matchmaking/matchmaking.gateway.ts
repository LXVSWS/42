import { OnGatewayConnection, OnGatewayDisconnect, SubscribeMessage, WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server } from 'socket.io';
import { v4 } from 'uuid';
import { gameRooms } from './sharedRooms';
import { GameRoom } from './gameRoom';
import { CustomSocket } from 'src/game/game.customSocket';
import { GameService } from 'src/game/game.service';
import { matchFriends } from './matchmaking.interface';
import { UsersService } from 'src/users/users.service';

@WebSocketGateway({
	namespace: 'matchmaking',
	cors: { origin: '*' }
})
export class MatchmakingGateway implements OnGatewayConnection, OnGatewayDisconnect {
	constructor(
		private gameService: GameService,
		private usersService: UsersService
	) { }

	@WebSocketServer() server: Server;
	private masterQueue: CustomSocket[][] = [[], [], []];
	private privateQueue: matchFriends[] = [];

	handleConnection(client: CustomSocket) {
		client.userId = client.handshake.auth.userId;
	}

	handleDisconnect(client: CustomSocket) {
		const index = this.privateQueue.findIndex(socket => socket.idP1 === client.userId);
		if (index !== -1) {
			// If the id is found in the array, remove the corresponding CustomSocket object
			this.privateQueue.splice(index, 1);
		}

		for (let i = 0; i < this.masterQueue.length; i++) {
			const sockets = this.masterQueue[i];
			const index = sockets.findIndex(socket => socket.userId === client.userId);

			if (index !== -1) {
				// If the id is found in the array, remove the corresponding CustomSocket object
				sockets.splice(index, 1);
				break;
			}
		}
	}

	@SubscribeMessage('newGameRequest')
	async handleNewGameRequest(client: CustomSocket, username: string) {
		const user = await this.usersService.getByUsername(username)
		if (user) {
			if (!this.privateQueue.find((user) => user.idP1 === client.userId)) {
				this.privateQueue.push({ idP1: client.userId, idP2: user.id, socketP1: client });
			}
		}
	}

	@SubscribeMessage('matchDenied')
	handleMatchDenied(client: CustomSocket) {
		const match = this.privateQueue.find((user) => user.idP1 === client.userId)
		if (match) {
			this.privateQueue.splice(this.privateQueue.indexOf(match));
		}
	}

	@SubscribeMessage('gameRequestAccepted')
	async handleGameRequestAccepted(client: CustomSocket, creatorUsername: string) {
		const creatorId = await this.usersService.getByUsername(creatorUsername);
		const match = this.privateQueue.find((user) => user.idP2 === client.userId && user.idP1 === creatorId.id)
		if (match) {
			const p1 = match.idP1;
			const p2 = match.idP2;
			const roomId = v4();

			const room = new GameRoom(this.gameService, roomId, 0, p1 , p2);
			gameRooms.push(room);
			match.socketP1.emit('matched', roomId);
			client.emit('matched', roomId);
			this.privateQueue.splice(this.privateQueue.indexOf(match), 1);
		}
	}

	@SubscribeMessage('joinQueue')
	joinQueue(client: CustomSocket, gameMode: number) {
		if (!this.masterQueue[gameMode].find((c) => (c.userId === client.userId))) {
			this.masterQueue[gameMode].push(client);
			this.matchPlayers(gameMode);
		}
	}

	@SubscribeMessage('leaveQueue')
	leaveQueue(client: CustomSocket, gameMode: number) {
		const index = this.masterQueue[gameMode].findIndex((c) => (c.userId === client.userId));
		if (index !== -1) {
			this.masterQueue[gameMode].splice(index, 1);
		}
	}

	// if 2 players in the array, match them and create a new room
	matchPlayers(gameMode: number) {
		if (this.masterQueue[gameMode].length >= 2) {
			const p1 = this.masterQueue[gameMode].shift();
			const p2 = this.masterQueue[gameMode].shift();
			const roomId = v4();

			// create a new room in the shared instance of GameRooms
			const room = new GameRoom(this.gameService, roomId, gameMode, p1.userId, p2.userId);
			gameRooms.push(room);

			// send roomId to players
			p2.emit('matched', roomId);
			p1.emit('matched', roomId);
		}
	}
}