import { Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import User from './entities/user.entity';
import FriendRequest from './friend-requests/entities/friend-request.entity';
import Avatar from './entities/avatar.entity';
import { FriendRequestsController } from './friend-requests/friend-requests.controller';
import { FriendRequestsService } from './friend-requests/friend-requests.service';
import { Profile } from './entities/profile.entity';
import { UserController } from './user/user.controller';

@Module({
  imports: [TypeOrmModule.forFeature([User, FriendRequest, Avatar, Profile])],
  providers: [
    UsersService,
    FriendRequestsService
  ],
  controllers: [
    UsersController,
    FriendRequestsController,
    UserController
  ],
  exports: [UsersService]
})
export class UsersModule {}
