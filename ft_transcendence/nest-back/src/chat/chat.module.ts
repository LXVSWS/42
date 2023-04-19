import { Module } from '@nestjs/common';
import { UsersModule } from 'src/users/users.module';
import { ChatGateway } from './chat.gateway';

@Module({
	imports: [UsersModule],
	providers: [ChatGateway]
})
export class ChatModule { }
