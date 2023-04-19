import { BadRequestException, Body, Controller, Get, Patch, Post, Query, Req, UseGuards } from "@nestjs/common";
import { RequestWithUser } from "src/auth/request-with-user.interface";
import JwtTwoFactorAuthGuard from "src/auth/two-factor-auth/jwt-two-factor-auth.guard";
import { UsersService } from "../users.service";
import RemoveFriendDto from "./dto/remove-friend.dto";
import UpdateAvatarDto from "./dto/update-avatar.dto";
import UpdateUsernameDto from "./dto/update-username.dto";
import BlockedDto from "./dto/block.dto";
import UnblockDto from "./dto/unblock.dto";
import usernameToId from "./dto/id.dto";

@Controller("user")
export class UserController {
	constructor(
		private usersService: UsersService
	) {}

	// returns what must be returned of user for frontend
	@Get()
	@UseGuards(JwtTwoFactorAuthGuard)
	async getUser(@Req() req: RequestWithUser) {
		const profile = await this.usersService.getProfile(req.user.id);
		return {
			id: req.user.id,
			isTwoFactorAuthenticationEnabled: req.user.isTwoFactorAuthenticationEnabled,
			blocked: req.user.blockedUser,
			profile
		}
	}

	@Patch("username")
	@UseGuards(JwtTwoFactorAuthGuard)
	async updateUsername(
		@Req() req: RequestWithUser,
		@Body() { newUsername }: UpdateUsernameDto
	) {
		const user = await this.usersService.getByUsername(newUsername);
		if (user) {
			throw new BadRequestException('User with that username already exists');
		}
		await this.usersService.setUsername(req.user.id, newUsername);
	}

	@Patch("avatar")
	@UseGuards(JwtTwoFactorAuthGuard)
	async updateAvatar(
		@Req() req: RequestWithUser,
		@Body() { newAvatar }: UpdateAvatarDto
	) {
		await this.usersService.setAvatar(req.user.id, newAvatar);
	}

	@Patch("remove-friend")
	@UseGuards(JwtTwoFactorAuthGuard)
	async removeFriends(
		@Req() req: RequestWithUser,
		@Body() { username }: RemoveFriendDto
	) {
		const friendToBeRemoved = await this.usersService.getByUsername(username);
		if (!friendToBeRemoved) {
			throw new BadRequestException("User with this username doesn't exist");
		}
		if (!this.usersService.areFriends(req.user.id, friendToBeRemoved.id)) {
			throw new BadRequestException("You are not friend with this user");
		}
		await this.usersService.removeFriends(req.user.id, friendToBeRemoved.id);
	}

	@Patch("id")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getId(
		@Req() req: RequestWithUser,
		@Body() { usernameToId }: usernameToId
	) {
		return (await this.usersService.getByUsername(usernameToId)).id;
	}
	
	@Get("friends")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getFriends(@Req() req: RequestWithUser) {
		const friends = await this.usersService.getFriends(req.user.id);
		const friendsProfiles = [];
		for (let i = 0; i < friends.length; i++) {
			const friendProfile = await this.usersService.getProfile(friends[i].id);
			friendsProfiles.push(friendProfile);
		}
		return friendsProfiles;
	}
	
	@Get("friend-requests")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getFriendRequests(@Req() req: RequestWithUser) {
		const friendRequests = await this.usersService.getFriendRequestsReceived(req.user.id);
		return Promise.all(friendRequests.map(async ({ id, creator, receiver }) => {
			const creatorProfile = await this.usersService.getProfile(creator.id);
			return {
				id,
				creator: creatorProfile
			};
		}));
	}


	@Patch("block-user")
	@UseGuards(JwtTwoFactorAuthGuard)
	async blockUser(
		@Req() req: RequestWithUser, 
		@Body() {usernameToBlock}: BlockedDto
	) {
		return await this.usersService.addBlockedUser(req.user.id, usernameToBlock);
	}

	@Patch("unblock-user")
	@UseGuards(JwtTwoFactorAuthGuard)
	async unblockUser(
		@Req() req: RequestWithUser,
		@Body() { usernameToUnblock }: UnblockDto
	) {
		return await this.usersService.removeBlockedUser(req.user.id, usernameToUnblock);
	}

	@Get("profile")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getProfile(@Req() req: RequestWithUser) {
		return this.usersService.getProfile(req.user.id);
	}

	@Get("profile-blocked-users")
	@UseGuards(JwtTwoFactorAuthGuard)
	async blockedUser(
		@Req() req: RequestWithUser,
	) {
		const blockedList = await this.usersService.getBlocked(req.user.id);
		const blockedListProfile = blockedList.map(async (user) => (await this.usersService.getProfile(user.id)));
		return await Promise.all(blockedListProfile);
	}

	@Get("blocked-users")
	@UseGuards(JwtTwoFactorAuthGuard)
	async getBlockedUser(@Req() req: RequestWithUser) {
		return this.usersService.getBlocked(req.user.id);
	}
}