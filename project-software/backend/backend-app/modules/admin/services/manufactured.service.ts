import { ManufacturedDto } from "../validations/dtos/manufactured.dto";
import createHttpError = require('http-errors');

export class ManufacturedService {

  async create(dto: ManufacturedDto) {
  }

  async createMany?(dto: any) {
    throw new Error('Method not implemented.');
  }

  async update(id: any, dto: any, condition?: any){
    throw new Error('Method not implemented.');
  }

  async find(dto?: any, id?: any) {
    throw new Error('Method not implemented.');
  }

  async findById(dto?: any, id?: any){
    throw new Error('Method not implemented.');
  }

  async delete(id: any) {
    throw new Error('Method not implemented.');
  }
}
