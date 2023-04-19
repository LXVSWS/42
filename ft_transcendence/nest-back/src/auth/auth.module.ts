import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { UsersModule } from 'src/users/users.module';
import { HttpModule } from '@nestjs/axios';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { JwtModule } from '@nestjs/jwt';
import { JwtStrategy } from './jwt.strategy';
import { TwoFactorAuthService } from './two-factor-auth/two-factor-auth.service';
import { TwoFactorAuthController } from './two-factor-auth/two-factor-auth.controller';
import { JwtTwoFactorStrategy } from './two-factor-auth/jwt-two-factor.strategy';

@Module({
  imports: [
    UsersModule,
    HttpModule,
    ConfigModule,
    JwtModule.registerAsync({
      imports: [ConfigModule],
      inject: [ConfigService],
      useFactory: async (configService: ConfigService) => ({
        secret: configService.get("JWT_SECRET"),
				signOptions: { expiresIn: `${configService.get("JWT_EXPIRATION_TIME")}s` }
      })
    })
  ],
  providers: [
    AuthService,
    JwtStrategy,
    TwoFactorAuthService,
    JwtTwoFactorStrategy
  ],
  controllers: [
    AuthController,
    TwoFactorAuthController
  ]
})
export class AuthModule {}
