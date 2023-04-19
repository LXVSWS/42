import { IsNotEmpty, IsString } from "class-validator";

export default class usernameToId {
	@IsString()
	@IsNotEmpty()
	usernameToId: string;
}