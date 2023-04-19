import { Column, Entity, OneToOne, PrimaryGeneratedColumn } from "typeorm";

@Entity()
class Avatar {
	@PrimaryGeneratedColumn()
	id: number;

	@Column()
	url: string;
}

export default Avatar;