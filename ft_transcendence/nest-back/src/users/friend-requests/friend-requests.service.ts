import { Injectable } from "@nestjs/common";
import { InjectRepository } from "@nestjs/typeorm";
import { Repository } from "typeorm";
import FriendRequest from "./entities/friend-request.entity";
import User from "../entities/user.entity";

@Injectable()
export class FriendRequestsService {
	constructor(
		@InjectRepository(FriendRequest) private friendRequestRepository: Repository<FriendRequest>
	) {}

	async getAll() {
		return this.friendRequestRepository.find();
	}

	async getOneByCreatorAndReceiver(creatorId: number, receiverId: number) {
		return this.friendRequestRepository.findOne({
			where: {
				creator: {
					id: creatorId
				},
				receiver: {
					id: receiverId
				}
			}
		})
	}

	async getById(id: number) {
		return this.friendRequestRepository.findOneBy({ id });
	}

	async create(creator: User, receiver: User) {
		const newFriendRequest = new FriendRequest();
		newFriendRequest.creator = creator;
		newFriendRequest.receiver = receiver;
		
		return this.friendRequestRepository.save(newFriendRequest);
	}

	async remove(friendRequestToBeRemoved: FriendRequest) {
		return this.friendRequestRepository.remove(friendRequestToBeRemoved);
	}
}