import { IsDateString, IsNotEmpty, IsString } from 'class-validator';

export class DeviceSyncDto {
  @IsString()
  @IsNotEmpty()
  serialNumber: string;

  @IsString()
  @IsNotEmpty()
  email: string;
}
