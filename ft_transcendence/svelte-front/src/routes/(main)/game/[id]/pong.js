export class gameInfo {
	constructor(width, heigth, gameMode) {
		this.gameMode = gameMode;
		this.canvasWidth = 1100;
		this.canvasHeight = 500;
		this.width = 1100;
		this.height = 500;
		this.border = 5;
		this.score = { p1: 0, p2: 0 }
	}

	drawMap(context) {
		context.strokeStyle = "hsl(201, 100%, 96%)";
		context.lineWidth = this.border * 2;
		context.fillStyle = "#b6b6f2";
		context.fillRect(0, 0, this.width, this.height);
		context.strokeRect(0, 0, this.width, this.height);
	}

	drawNet(context) {
		context.lineWidth = this.border;
		context.beginPath();
		context.moveTo(this.width / 2, 0);
		context.lineTo(this.width / 2, this.height);
		context.closePath();
		context.stroke();
	}
}

export class paddle {
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

	draw(context) {
		context.fillStyle = "hsl(201, 100%, 96%)";
		context.fillRect(
			this.x,
			this.y,
			this.player_width,
			this.player_height
		);
	}
}

export class ball {
	constructor(game, rand) {
		this.x = game.width / 2;
		this.y = game.height / 2;

		this.radius = game.gameMode == 1 ? 3 : 7;
		this.x_vel = 0;
		this.y_vel = 0;
	}

	new(ball) {
		this.x = ball.x;
		this.y = ball.y;

		this.radius = ball.radius;
		this.x_vel = ball.x_vel;
		this.y_vel = ball.y_vel;
	}

	reset(game, rand) {
		this.x = game.width / 2;
		this.y = game.height / 2;
		this.x_vel = game.gameMode == 1 ? -6 : -4 * rand.x;
		this.y_vel = game.gameMode == 1 ? -6 : -4 * rand.y;
	}

	update(elapsedTime) {
		this.x += this.x_vel * (elapsedTime / 1.2);
		this.y += this.y_vel * (elapsedTime / 1.2);
	}

	newCollision(new_x_vel, new_y_vel) {
		this.x_vel = new_x_vel;
		this.y_vel = new_y_vel;
	}

	draw(context) {
		context.beginPath();
		context.arc(this.x, this.y, this.radius, 0, Math.PI * 2, true);
		context.fill();
	}
}

export function waitFlip() {
	return new Promise(resolve => {
		if (window.innerHeight > window.innerWidth) {
			setTimeout(function () { resolve(waitFlip()) }, 500);
		}
		else {
			resolve(false);
		}
	});
}