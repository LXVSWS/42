import { BadRequestException, Body, Controller, Get, HttpCode, Post, Redirect, Req, Res, UnauthorizedException, UseGuards } from "@nestjs/common";
import { Response } from "express";
import { UsersService } from "src/users/users.service";
import { AuthService } from "../auth.service";
import JwtAuthGuard from "../jwt-auth.guard";
import { RequestWithUser } from "../request-with-user.interface";
import TwoFactorAuthCodeDto from "./dto/two-factor-auth-code.dto";
import JwtTwoFactorAuthGuard from "./jwt-two-factor-auth.guard";
import { TwoFactorAuthService } from "./two-factor-auth.service";
import { ConfigService } from "@nestjs/config";

@Controller("2fa")
export class TwoFactorAuthController {
	constructor(
		private twoFactorAuthService: TwoFactorAuthService,
		private usersService: UsersService,
		private authService: AuthService,
		private configService: ConfigService
	) {}

	@Get("redirect")
	@Redirect()
	redirect() {
		return {
			// url: `http://${this.configService.get("VITE_HOST")}:${this.configService.get("SVELTEKIT_PORT")}`,
			url: `http://${this.configService.get("VITE_HOST")}`,
			statusCode: 302
		}
	}

	@Post("generate")
	@UseGuards(JwtAuthGuard)
  	async register(@Req() req: RequestWithUser) {
		const { otpauthUrl } = await this.twoFactorAuthService.generateTwoFactorAuthenticationSecret(req.user.id, req.user.email);
		return this.twoFactorAuthService.generateQrCodeDataURL(otpauthUrl);
  	}

	@Post("turn-on")
	@UseGuards(JwtAuthGuard)
	@HttpCode(200)
	async turnOnTwoFactorAuthentication(
		@Req() req: RequestWithUser,
		@Body() { twoFactorAuthenticationCode }: TwoFactorAuthCodeDto
	) {
		const isCodeValid = this.twoFactorAuthService.isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode, req.user.twoFactorAuthenticationSecret);
		if (!isCodeValid) {
			throw new BadRequestException('Wrong authentication code');
		}
		await this.usersService.turnOnTwoFactorAuthentication(req.user.id);
	}

	@Post("turn-off")
	@UseGuards(JwtTwoFactorAuthGuard)
	@HttpCode(200)
	async turnOffTwoFactorAuthentication(@Req() req: RequestWithUser) {
		await this.usersService.turnOffTwoFactorAuthentication(req.user.id);
	}

	@Post("login")
	@UseGuards(JwtAuthGuard)
	@HttpCode(200)
	async login(
		@Req() req: RequestWithUser,
		@Res({ passthrough: true }) res: Response,
		@Body() { twoFactorAuthenticationCode }: TwoFactorAuthCodeDto
	) {
		const isCodeValid = this.twoFactorAuthService.isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode, req.user.twoFactorAuthenticationSecret);
		if (!isCodeValid) {
			throw new BadRequestException("Wrong authentication code");
		}
		const cookie = this.authService.getCookieWithJwtAccessToken(req.user.id, true);
		res.setHeader("Set-Cookie", cookie);
	}
}