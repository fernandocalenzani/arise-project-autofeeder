import IRepository from '../IRepositiry';
import { IUser } from '../../models/user.model';
import { Model } from 'mongoose';
import { UpdateUserDto } from '../../modules/user/validations/dtos/update-user.dto';
import { CreateUserDto } from '../../modules/user/validations/dtos/create-user.dto';

export class UserRepository implements IRepository {
  private userModel: any;

  constructor(userModel: Model<IUser>) {
    this.userModel = userModel;
  }

  async create(payload: CreateUserDto) {
    return await this.userModel.create(payload);
  }

  async update(id: any, payload: UpdateUserDto) {
    return await this.userModel.findOneAndUpdate({ _id: id }, payload, {
      new: true,
    });
  }

  async findAll() {
    return await this.userModel.findAll();
  }

  async findById(id: any) {
    return await this.userModel.findById(id);
  }

  async delete(id: any) {
    return await this.userModel.delete({ _id: id });
  }

  async count(payload: any) {
    return await this.userModel.count(payload);
  }

  async createMany?(payload: any) {
    throw new Error('Method not implemented.');
  }
  async find(payload?: any, id?: any) {
    throw new Error('Method not implemented.');
  }
}
