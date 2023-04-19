import { Injectable } from "@nestjs/common";
import { UsersService } from "src/users/users.service";
import { authenticator } from 'otplib';
import * as qrcode from "qrcode";
import { ConfigService } from "@nestjs/config";

@Injectable()
export class TwoFactorAuthService {
	constructor(
		private usersService: UsersService,
    private configService: ConfigService
	) {}

	async generateTwoFactorAuthenticationSecret(userId: number, userEmail: string) {
    const secret = authenticator.generateSecret();
    const otpauthUrl = authenticator.keyuri(userEmail, this.configService.get("AUTH_APP_NAME"), secret);
    await this.usersService.setTwoFactorAuthenticationSecret(secret, userId);
    return { otpauthUrl };
  }

	async generateQrCodeDataURL(otpAuthUrl: string): Promise<any> {
		return qrcode.toDataURL(otpAuthUrl, {
			width: 300,
			height: 300
		});
  }

	isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode: string, userTwoFactorAuthenticationSecret: string): boolean {
    return authenticator.verify({
      token: twoFactorAuthenticationCode,
      secret: userTwoFactorAuthenticationSecret
    });
  }
}