import { IsBoolean, IsNotEmpty, IsNumber, IsString } from 'class-validator';

export class DeviceSettingsDto {
  @IsString()
  @IsNotEmpty()
  serialNumber: string;

  @IsString()
  @IsNotEmpty()
  applications: string[];

  @IsBoolean()
  @IsNotEmpty()
  operation: boolean;

  @IsNumber()
  @IsNotEmpty()
  gmt: number;

  @IsNumber()
  @IsNotEmpty()
  ktm: number;
}
