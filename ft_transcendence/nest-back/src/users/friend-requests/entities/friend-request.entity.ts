import { Column, Entity, JoinColumn, JoinTable, ManyToMany, ManyToOne, OneToMany, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import User from "../../entities/user.entity";

/*
	notes
		- add a createdAt column so friendRequest could expire
*/

@Entity()
class FriendRequest {
	@PrimaryGeneratedColumn()
	id: number;

	@ManyToOne(type => User, user => user.friendRequestsCreated, {
		eager: true
	})
	creator: User;

	@ManyToOne(type => User, user => user.friendRequestsReceived, {
		eager: true
	})
	receiver: User;
}

export default FriendRequest;