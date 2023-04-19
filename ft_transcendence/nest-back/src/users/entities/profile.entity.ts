import { Column, Entity, JoinColumn, OneToOne, PrimaryGeneratedColumn } from "typeorm";
import Avatar from "./avatar.entity";

@Entity()
export class Profile {
	@PrimaryGeneratedColumn()
	id: number;

	@Column({ unique: true })
	username: string;

	@Column({ default: 0 })
	wins: number;

	@Column({ default: 0 })
	losses: number;

	@OneToOne(type => Avatar, {
		eager: true,
		cascade: true
	})
	@JoinColumn()
	avatar: Avatar;
}