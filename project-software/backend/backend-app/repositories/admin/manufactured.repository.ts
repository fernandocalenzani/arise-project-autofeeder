import IRepository from '../IRepositiry';
import { IManufactured } from '../../models/manufactured.model';
import { Model } from 'mongoose';
import { ManufacturedDto } from '../../modules/admin/validations/dtos/manufactured.dto';

export class ManufacturedRepository implements IRepository {
  private manufacturedModel: any;

  constructor(manufacturedModel: Model<IManufactured>) {
    this.manufacturedModel = manufacturedModel;
  }

  async create(payload: any) {
    return await this.manufacturedModel.create(payload);
  }

  async createMany?(payload: any) {
    return await this.manufacturedModel.insertMany(payload);
  }

  async update(id: any, payload: ManufacturedDto) {
    return await this.manufacturedModel.findOneAndUpdate({ _id: id }, payload, {
      new: true,
    });
  }

  async find(payload?: any, id?: any) {
    return await this.manufacturedModel.find(payload);
  }

  async findAll(payload?: any) {}

  async findById(id?: any) {
    return await this.manufacturedModel.findById(id);
  }

  async delete(id: any) {
    return await this.manufacturedModel.deleteOne({ _id: id });
  }

  async count(payload: any) {
    return await this.manufacturedModel.count(payload);
  }
}
