import { IsNotEmpty, IsString } from "class-validator";

export default class UnblockDto {
	@IsString()
	@IsNotEmpty()
	usernameToUnblock: string;
}