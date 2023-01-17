import { IsDateString, IsNotEmpty, IsString } from 'class-validator';

export class ManufacturedDto {
  @IsString()
  @IsNotEmpty()
  serialNumber: string;

  @IsString()
  @IsNotEmpty()
  model: string;

  @IsDateString()
  @IsNotEmpty()
  manufacturingDate: Date;
}
