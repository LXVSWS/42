import { Column, Entity, JoinColumn, JoinTable, ManyToMany, ManyToOne, OneToMany, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import FriendRequest from "../friend-requests/entities/friend-request.entity";
import { Profile } from "./profile.entity";
import { Match } from "../../game/entities/match.entity";

@Entity()
class User {
	@PrimaryGeneratedColumn()
	id: number;

	@Column({ unique: true })
	email: string;

	@Column({ nullable: true, default: null })
	twoFactorAuthenticationSecret: string;

	@Column({ default: false })
	isTwoFactorAuthenticationEnabled: boolean;

	@ManyToMany(type => User, user => user.blockedUser)
	@JoinTable()
	blockedUser: User[];

	@OneToOne(type => Profile, {
		cascade: true
	})
	@JoinColumn()
	profile: Profile;

	@ManyToMany(type => User, user => user.friends)
	@JoinTable()
	friends: User[];

	@OneToMany(type => FriendRequest, friendRequest => friendRequest.creator)
	friendRequestsCreated: FriendRequest[];

	@OneToMany(type => FriendRequest, friendRequest => friendRequest.receiver)
	friendRequestsReceived: FriendRequest[];

	@OneToMany(type => Match, match => match.winner)
	matchesWon: Match[];

	@OneToMany(type => Match, match => match.loser)
	matchesLost: Match[];
}

export default User;