import { Module } from '@nestjs/common';
import { GameModule } from 'src/game/game.module';
import { UsersModule } from 'src/users/users.module';
import { MatchmakingGateway } from './matchmaking.gateway';

@Module({
	providers: [
		MatchmakingGateway
	],
	imports: [UsersModule, GameModule]
})
export class MatchmakingModule { }
