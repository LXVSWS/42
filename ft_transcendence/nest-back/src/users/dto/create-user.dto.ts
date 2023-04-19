import { IsEmail, IsNotEmpty, IsString, Length, Matches } from "class-validator";

class CreateUserDto {
	@IsEmail()
	@IsNotEmpty()
	email: string;

	@IsString()
	@IsNotEmpty()
  	username: string;

	@IsString()
	@IsNotEmpty()
	avatarUrl: string;
}

export default CreateUserDto;