import { ball, paddle, gameInfo } from "./pong";
import { GameService } from "src/game/game.service";

export class GameRoom {
	public id: string;
	public playersMap: Map<number, boolean> = new Map<number, boolean>();
	public player: number[] = new Array(2);
	public spectators: number[] = [];
	public gameMode: number;
	public score: number[] = [0, 0];
	public ready: Boolean = true;
	public nbPlayerRdy: number = 0;
	public index: number = 0;
	public end: boolean = false;
	public ball: ball;
	public paddle1: paddle;
	public paddle2: paddle;
	public gameInfo: gameInfo;
	public intervalId: NodeJS.Timer;

	constructor(private gameService: GameService, id: string, gameMode: number, player1: number, player2: number) {
		this.id = id;
		this.gameMode = gameMode;
		this.playersMap.set(player1, false);
		this.playersMap.set(player2, false);
	}

	startGame(server) {
		let DIRECTION = {
			IDLE: 0,
			UP: 1,
			DOWN: 2,
		};
		//init game Objects
		this.gameInfo = new gameInfo(this.gameMode);
		this.ball = new ball(this.gameInfo);
		this.paddle1 = new paddle(this.gameInfo, true);
		this.paddle2 = new paddle(this.gameInfo, false);

		// main loop that run every updateInterval (30 * per sec)
		this.ball.reset([Math.random() < 0.5 ? 1 : -1, Math.random() < 0.5 ? 1 : -1])
		this.intervalId = setInterval(async () => {
			if (this.ball.y - this.ball.radius <= 0 && this.ball.y_vel < 0) {
				this.ball.y_vel *= -1;
			} else if (this.ball.y + this.ball.radius >= this.gameInfo.height && this.ball.y_vel > 0) {
				this.ball.y_vel *= -1;
			}

			// Collision with paddle 1
			if (
				this.ball.y + this.ball.radius >= this.paddle1.y &&
				this.ball.y - this.ball.radius <= this.paddle1.y + this.paddle1.player_height &&
				this.ball.x + this.ball.radius >= this.paddle1.x &&
				this.ball.x - this.ball.radius <= this.paddle1.x + this.paddle1.player_width &&
				this.ball.x_vel < 0
			) {
				this.ball.x_vel *= -1.1
				this.ball.y_vel *= 1.1;
				if (this.gameInfo.gameMode === 2) server.to(this.id).emit("resetOpacity");
			}

			// Collision with paddle 2
			if (
				this.ball.y + this.ball.radius >= this.paddle2.y &&
				this.ball.y - this.ball.radius <= this.paddle2.y + this.paddle2.player_height &&
				this.ball.x + this.ball.radius >= this.paddle2.x &&
				this.ball.x - this.ball.radius <= this.paddle2.x + this.paddle2.player_width &&
				this.ball.x_vel > 0
			) {
				this.ball.x_vel *= -1.1
				this.ball.y_vel *= 1.1;
				if (this.gameInfo.gameMode === 2) server.to(this.id).emit("resetOpacity");
			}

			if (this.ball.x < 0 || this.ball.x > this.gameInfo.width) {
				if (this.ball.x < 0) {
					// p2 scores
					this.score[1]++;
				} else if (this.ball.x > this.gameInfo.width) {
					// p1 scores
					this.score[0]++;
				}
				if (this.score[0] >= 5 || this.score[1] >= 5) {
					clearInterval(this.intervalId);
					this.end = true;
					this.gameService.save(this.score, this.player);
					server.to(this.id).emit('endGame');
					return true;
				}
				//reset the ball
				server.to(this.id).emit('updateScore', this.score);
				this.ball.reset([Math.random() < 0.5 ? 1 : -1, Math.random() < 0.5 ? 1 : -1]);
				server.to(this.id).emit('updateBall', [this.ball.x, this.ball.y]);
				if (this.gameInfo.gameMode === 2) server.to(this.id).emit("resetOpacity");
			}

			if (this.paddle1.dir == DIRECTION.UP && this.paddle1.y > 0) {
				this.paddle1.y -= this.paddle1.speed;
			} else if (
				this.paddle1.dir == DIRECTION.DOWN &&
				this.paddle1.y + this.paddle1.player_height < this.gameInfo.height
			) {
				this.paddle1.y += this.paddle1.speed;
			}
			if (this.paddle2.dir == DIRECTION.UP && this.paddle2.y > 0) {
				this.paddle2.y -= this.paddle2.speed;
			} else if (
				this.paddle2.dir == DIRECTION.DOWN &&
				this.paddle2.y + this.paddle2.player_height < this.gameInfo.height
			) {
				this.paddle2.y += this.paddle2.speed;
			}

			this.ball.update();
			server.to(this.id).emit('updateBall', [this.ball.x, this.ball.y]);
		}, this.gameInfo.updateInterval);
		return false;
	}

	isPlayer(client: number) {
		return this.playersMap.has(client);
	}

	isSpecator(client: number) {
		return this.spectators.includes(client);
	}

}