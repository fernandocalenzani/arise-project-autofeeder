import IRepository from '../IRepositiry';
import { Model } from 'mongoose';
import { IDeviceSync } from '../../models/device-sync.model';
import { DeviceSyncDto } from '../../modules/devicesync/services/dtos/device-sync.dto';

export class DeviceSyncRepository implements IRepository {
  private devicesyncModel: any;

  constructor(devicesyncModel: Model<IDeviceSync>) {
    this.devicesyncModel = devicesyncModel;
  }

  async create(payload: DeviceSyncDto) {
    return await this.devicesyncModel.create(payload);
  }

  async update(id: any, payload: DeviceSyncDto) {
    return await this.devicesyncModel.findOneAndUpdate({ _id: id }, payload, {
      new: true,
    });
  }

  async findAll() {
    return await this.devicesyncModel.findAll();
  }

  async findById(id: any) {
    return await this.devicesyncModel.findById(id);
  }

  async delete(id: any) {
    return await this.devicesyncModel.delete({ _id: id });
  }

  async count(payload: any) {
    return await this.devicesyncModel.count(payload);
  }

  async createMany?(payload: any) {
    throw new Error('Method not implemented.');
  }
  async find(payload?: any, id?: any) {
    throw new Error('Method not implemented.');
  }
}
