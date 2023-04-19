import { IsNotEmpty, IsString } from "class-validator";

export default class RemoveFriendDto {
	@IsString()
	@IsNotEmpty()
	username: string;
}