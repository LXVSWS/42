import { IsNotEmpty, IsString } from "class-validator";

export default class UpdateAvatarDto {
	@IsString()
	@IsNotEmpty()
	newAvatar: string;
}