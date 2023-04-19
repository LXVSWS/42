import { HttpService } from '@nestjs/axios';
import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { JwtService } from '@nestjs/jwt';
import User from 'src/users/entities/user.entity';
import { UsersService } from 'src/users/users.service';
import { TokenPayload } from './token-payload.interface';
import { uniqueNamesGenerator, adjectives } from 'unique-names-generator';

@Injectable()
export class AuthService {
	constructor(
		private usersService: UsersService,
		private httpService: HttpService,
		private jwtService: JwtService,
		private configService: ConfigService
	) { }

	async getAccessToken42(code: string): Promise<string> {
		const res = await this.httpService.axiosRef.post("https://api.intra.42.fr/oauth/token", {
			grant_type: "authorization_code",
			client_id: this.configService.get("VITE_INTRA_CLIENT_UID"),
			client_secret: this.configService.get("INTRA_SECRET"),
			code: code,
			redirect_uri: `http://${this.configService.get("VITE_HOST")}:${this.configService.get("VITE_NESTJS_PORT")}/auth/login`
		});
		return res.data?.access_token;
	}

	async getAccessToken42Info(accessToken42: string): Promise<any> {
		const res = await this.httpService.axiosRef.get("https://api.intra.42.fr/oauth/token/info", {
			headers: {
				Authorization: `Bearer ${accessToken42}`
			}
		});
		return res.data;
	}

	async getUser42Info(accessToken42: string): Promise<any> {
		const res = await this.httpService.axiosRef.get("https://api.intra.42.fr/v2/me", {
			headers: {
				Authorization: `Bearer ${accessToken42}`
			}
		});
		return res.data;
	}

	async register(user42: any): Promise<User> {
		const { email, login, image, ...rest } = user42;
		let randomAdjdective = uniqueNamesGenerator({ dictionaries: [adjectives] });
		let username = login + "-" + randomAdjdective;
		let user = await this.usersService.getByUsername(username);
		while (user) {
			randomAdjdective = uniqueNamesGenerator({ dictionaries: [adjectives] });
			username = login + "-" + randomAdjdective;
			user = await this.usersService.getByUsername(username);
		}
		const newUser = await this.usersService.create({
			email: email,
			username: username,
			avatarUrl: image.versions.large
		});
		return newUser;
	}

	getCookieWithJwtAccessToken(userId: number, isTwoFactorAuthenticated = false) {
		const payload: TokenPayload = {
			userId,
			isTwoFactorAuthenticated
		};
		const token = this.jwtService.sign(payload);
		return `Authentication=${token}; HttpOnly; Path=/; Max-Age=${this.configService.get('JWT_EXPIRATION_TIME')}`;
	}

	getCookieForLogOut() {
		return `Authentication=; HttpOnly; Path=/; Max-Age=0`;
	}
}
