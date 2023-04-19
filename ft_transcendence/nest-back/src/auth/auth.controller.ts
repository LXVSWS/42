import { Controller, Get, HttpException, HttpStatus, NotFoundException, Query, Redirect, Req, Res, UseGuards } from '@nestjs/common';
import { Response } from 'express';
import { PostgresErrorCode } from 'src/database/postges-error-code';
import { UsersService } from 'src/users/users.service';
import { AuthService } from './auth.service';
import { RequestWithUser } from './request-with-user.interface';
import JwtTwoFactorAuthGuard from './two-factor-auth/jwt-two-factor-auth.guard';
import { ConfigService } from '@nestjs/config';

@Controller('auth')
export class AuthController {
	constructor(
		private authService: AuthService,
		private usersService: UsersService,
		private configService: ConfigService
	) { }

	// --- begin testing ---
	// @Get("username")
	// @Redirect()
	// async loginWithUsername(
	// 	@Res({ passthrough: true }) res: Response,
	// 	@Query("username") username: string
	// ) {
	// 	let user = await this.usersService.getByUsername(username);
	// 	if (!user) {
	// 		throw new NotFoundException();
	// 	}
	// 	const cookie = this.authService.getCookieWithJwtAccessToken(user.id);
	// 	res.setHeader("Set-Cookie", cookie);
	// 	return {
	// 		url: `http://${this.configService.get("VITE_HOST")}:${this.configService.get("SVELTEKIT_PORT")}`,
	// 		// url: `http://${this.configService.get("VITE_HOST")}`,
	// 		statusCode: 302
	// 	}
	// }
	// --- end testing ---

	// callback endpoint to be supplied to 42 intra app page
	@Get("login")
	@Redirect()
	async login(
		@Res({ passthrough: true }) res: Response,
		@Query("code") code: string
	) {
		const accessToken42 = await this.authService.getAccessToken42(code);
		const user42 = await this.authService.getUser42Info(accessToken42);
		let user = await this.usersService.getByEmail(user42.email);
		if (!user) {
			try {
				user = await this.authService.register(user42);
			} catch (error) {
				if (error.code === PostgresErrorCode.UniqueViolation) {
					throw new HttpException('User with that email already exists', HttpStatus.BAD_REQUEST);
				}
				// we might log this error
				throw new HttpException('Something went wrong', HttpStatus.INTERNAL_SERVER_ERROR);
			}
		}
		const cookie = this.authService.getCookieWithJwtAccessToken(user.id);
		res.setHeader("Set-Cookie", cookie);
		return {
			// url: user.isTwoFactorAuthenticationEnabled ? `http://${this.configService.get("VITE_HOST")}:${this.configService.get("SVELTEKIT_PORT")}/2fa/verify` : `http://${this.configService.get("VITE_HOST")}:${this.configService.get("SVELTEKIT_PORT")}`,
			url: user.isTwoFactorAuthenticationEnabled ? `http://${this.configService.get("VITE_HOST")}/2fa/verify` : `http://${this.configService.get("VITE_HOST")}`,
			statusCode: 302
		};
	}

	@Get("logout")
	@UseGuards(JwtTwoFactorAuthGuard)
	logout(@Res({ passthrough: true }) res: Response) {
		const cookie = this.authService.getCookieForLogOut();
		res.setHeader("Set-Cookie", cookie);
	}
}
