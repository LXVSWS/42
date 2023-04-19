import { IsNotEmpty, IsString, Matches } from "class-validator";

export default class UpdateUsernameDto {
	@IsString()
	@IsNotEmpty()
	@Matches(/^[-_a-zA-Z0-9]{5,25}$/, {
		message: "min-length: 5; max-length: 25; characters: alphanumeric, '-' and '_'"
	})
	newUsername: string;
}