import { IsNotEmpty, IsString } from "class-validator";

export default class CreateFriendRequestDto {
	@IsString()
	@IsNotEmpty()
	username: string;
}