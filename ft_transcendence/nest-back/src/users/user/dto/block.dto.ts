import { IsNotEmpty, IsString } from "class-validator";

export default class BlockedDto {
	@IsString()
	@IsNotEmpty()
	usernameToBlock: string;
}