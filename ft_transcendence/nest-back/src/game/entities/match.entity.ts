import { Column, CreateDateColumn, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import User from "../../users/entities/user.entity";

@Entity()
export class Match {
	@PrimaryGeneratedColumn()
	id: number;

	@Column()
	scoreWinner: number;

	@Column()
	scoreLoser: number;

	@ManyToOne(type => User, { eager: true })
	winner: User;

	@ManyToOne(type => User, { eager: true })
	loser: User;

	@CreateDateColumn()
	createdAt: Date;

}