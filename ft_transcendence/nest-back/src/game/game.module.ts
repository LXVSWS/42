import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { MatchmakingModule } from 'src/matchmaking/matchmaking.module';
import { UsersModule } from 'src/users/users.module';
import { Match } from './entities/match.entity';
import { GameController } from './game.controller';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';

@Module({
	imports: [TypeOrmModule.forFeature([Match]), UsersModule],
	providers: [GameGateway, GameService],
	controllers: [GameController],
	exports: [GameService, TypeOrmModule]
})
export class GameModule { }
