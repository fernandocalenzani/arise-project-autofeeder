import { IsDateString, IsNotEmpty, IsString } from 'class-validator';

export class UpdateDevicesDto {
  @IsDateString()
  @IsNotEmpty()
  timeUpdateFirmware: Date;

  @IsString()
  @IsNotEmpty()
  newVersion: string;

  @IsString()
  @IsNotEmpty()
  currentVersion: string;

  @IsString()
  @IsNotEmpty()
  keyOTA: string;

  @IsString()
  @IsNotEmpty()
  serialNumber: string;
}
