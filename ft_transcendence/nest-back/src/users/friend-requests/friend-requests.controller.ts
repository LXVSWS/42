import { BadRequestException, Body, Controller, Delete, Get, HttpException, Param, ParseIntPipe, Post, Req, UseGuards } from "@nestjs/common";
import { RequestWithUser } from "src/auth/request-with-user.interface";
import JwtTwoFactorAuthGuard from "src/auth/two-factor-auth/jwt-two-factor-auth.guard";
import { UsersService } from "../users.service";
import CreateFriendRequestDto from "./dto/create-friend-request.dto";
import { FriendRequestsService } from "./friend-requests.service";

/*
	notes
		- remove sensitive returns
*/

@Controller("friend-requests")
export class FriendRequestsController {
	constructor(
		private friendRequestsService: FriendRequestsService,
		private usersService: UsersService
	) {}

	// --- begin testing ---
	// @Get()
	// async getAll() {
	// 	return this.friendRequestsService.getAll();
	// }

	// @Delete(":id")
	// async remove(@Param("id", ParseIntPipe) id: number) {
	// 	const fr = await this.friendRequestsService.getById(id);
	// 	if (!fr) {
	// 		throw new BadRequestException();
	// 	}
	// 	return this.friendRequestsService.remove(fr);
	// }
	// --- end testing ---

	@Post()
	@UseGuards(JwtTwoFactorAuthGuard)
	async send(
		@Req() req: RequestWithUser,
		@Body() { username }: CreateFriendRequestDto
	) {
		const creator = req.user;
		const receiver = await this.usersService.getByUsername(username);
		if (!receiver) {
			throw new BadRequestException("User with that username doesn't exist");
		}
		if (creator.id === receiver.id) {
			throw new BadRequestException("Pls find a real friend");
		}
		if (await this.usersService.areFriends(creator.id, receiver.id)) {
			throw new BadRequestException("You are already friend with this user");
		}
		const friendRequestFirstWay = await this.friendRequestsService.getOneByCreatorAndReceiver(creator.id, receiver.id);
		if (friendRequestFirstWay) {
			throw new BadRequestException("Friend request already exists");
		}
		const friendRequestSecondWay = await this.friendRequestsService.getOneByCreatorAndReceiver(receiver.id, creator.id);
		if (friendRequestSecondWay) {
			throw new BadRequestException("Friend request already exists");
		}
		const newFriendRequest = await this.friendRequestsService.create(creator, receiver);
		const creatorProfile = await this.usersService.getProfile(creator.id);
		const receiverProfile = await this.usersService.getProfile(receiver.id);
		return { id: newFriendRequest.id, creator: creatorProfile, receiver: receiverProfile };
	}

	@Post("accept/:id")
	@UseGuards(JwtTwoFactorAuthGuard)
	async accept(
		@Req() req: RequestWithUser,
		@Param("id", ParseIntPipe) id: number
	) {
		const friendRequestToBeAccepted = await this.friendRequestsService.getById(id);
		if (!friendRequestToBeAccepted) {
			throw new BadRequestException("Friend request with that id doesn't exist");
		}
		if (req.user.id !== friendRequestToBeAccepted.receiver.id) {
			throw new BadRequestException("You can't accept someone's else friend request");
		}
		await this.usersService.makeFriends(friendRequestToBeAccepted.receiver.id, friendRequestToBeAccepted.creator.id);
		await this.friendRequestsService.remove(friendRequestToBeAccepted);
		return this.usersService.getProfile(friendRequestToBeAccepted.creator.id);
	}

	@Post("decline/:id")
	@UseGuards(JwtTwoFactorAuthGuard)
	async decline(
		@Req() req: RequestWithUser,
		@Param("id", ParseIntPipe) id: number
	) {
		const friendRequestToBeRemoved = await this.friendRequestsService.getById(id);
		if (!friendRequestToBeRemoved) {
			throw new BadRequestException("Friend request with that id doesn't exist");
		}
		if (req.user.id !== friendRequestToBeRemoved.receiver.id) {
			throw new BadRequestException("You can't decline someone's else friend request");
		}
		await this.friendRequestsService.remove(friendRequestToBeRemoved);
	}
}