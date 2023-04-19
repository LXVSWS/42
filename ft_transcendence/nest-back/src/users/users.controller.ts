import { BadRequestException, Controller, Delete, Get, NotFoundException, Param, ParseIntPipe, Post, UseGuards } from '@nestjs/common';
import JwtTwoFactorAuthGuard from 'src/auth/two-factor-auth/jwt-two-factor-auth.guard';
import { UsersService } from './users.service';

@Controller('users')
export class UsersController {
	constructor(private usersService: UsersService) { }

	// --- begin testing ---
	// countFakeUser = 0;

	// @Get()
	// findAll() {
	// 	return this.usersService.getAll();
	// }

	// @Post("fake")
	// addFakeUser() {
	// 	const fakeUser = {
	// 		email: `test${this.countFakeUser}@gmail.com`,
	// 		username: `test${this.countFakeUser}`,
	// 		avatarUrl: "https://picsum.photos/200"
	// 	};
	// 	this.countFakeUser++;
	// 	return this.usersService.create(fakeUser);
	// }

	// @Delete(":id")
	// remove(@Param("id", ParseIntPipe) id: number) {
	// 	return this.usersService.remove(id);
	// }
	// --- end testing ---

	@Get(":id")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getUser(@Param("id", ParseIntPipe) id: number) {
		const user = this.usersService.getById(id);
		if (!user) {
			throw new NotFoundException();
		}
		return user;
	}

	@Get("profile/:username")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getProfile(@Param("username") username: string) {
		const user = await this.usersService.getByUsername(username);
		if (!user) {
			throw new BadRequestException();
		}
		return this.usersService.getProfile(user.id);
	}
}
