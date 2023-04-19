import { IsNotEmpty, IsString } from "class-validator";

export default class TwoFactorAuthCodeDto {
	@IsString()
	@IsNotEmpty()
	twoFactorAuthenticationCode: string;
}