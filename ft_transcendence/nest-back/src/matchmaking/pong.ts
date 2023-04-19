export class gameInfo {
	gameMode: number;
	canvasWidth: number;
	canvasHeight: number;
	width: number;
	height: number;
	border: number;
	score: { p1: number; p2: number; };
	updateInterval: number;
	constructor(gameMode) {
		this.gameMode = gameMode;
		this.canvasWidth = 1100;
		this.canvasHeight = 500;
		this.width = 1100;
		this.height = 500;
		this.border = 5;
		this.score = { p1: 0, p2: 0 }
		this.updateInterval = 1000 / 60;
	}
}

export class paddle {
	player_height: number;
	player_width: number;
	x: number;
	y: number;
	speed: number;
	dir: number;
	constructor(game, isPlayer1) {
		this.player_height = game.height / 7;
		this.player_width = 10;
		this.x = isPlayer1 ? 30 : game.width - 30 - this.player_width;
		this.y = game.height / 2 - this.player_height / 2;
		this.speed = 5;
		this.dir = 0;
	}

	reset(game, isPlayer1) {
		this.player_height = game.height / 7;
		this.player_width = 10;
		this.x = isPlayer1 ? 30 : game.width - 30 - this.player_width;
		this.y = game.height / 2 - this.player_height / 2;
		this.speed = 5;
		this.dir = 0;
	}
}

export class ball {
	x: number;
	y: number;
	radius: number;
	x_vel: number;
	y_vel: number;
	game: gameInfo;
	constructor(game) {
		this.x = game.width / 2;
		this.y = game.height / 2;

		this.radius = game.gameMode == 1 ? 3 : 7;
		this.game = game;
		this.x_vel = 0;
		this.y_vel = 0;
	}

	reset(rand) {
		this.x = this.game.width / 2;
		this.y = this.game.height / 2;
		this.x_vel = this.game.gameMode == 1 ? -6 : -4 * rand[0];
		this.y_vel = this.game.gameMode == 1 ? -6 : -4 * rand[1];
	}

	update() {
		this.x += this.x_vel;
		this.y += this.y_vel;
	}

	newCollision(new_x_vel, new_y_vel) {
		this.x_vel = new_x_vel;
		this.y_vel = new_y_vel;
	}
}