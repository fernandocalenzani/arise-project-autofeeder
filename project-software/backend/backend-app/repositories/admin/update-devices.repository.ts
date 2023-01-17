import IRepository from '../IRepositiry';
import { IUpdateDevices } from '../../models/update-devices.model';
import { Model } from 'mongoose';
import { UpdateDevicesDto } from '../../modules/admin/validations/dtos/update-devices.dto';

export class UpdateDevicesRepository implements IRepository {
  private updateDeviceModel: any;

  constructor(updateDeviceModel: Model<IUpdateDevices>) {
    this.updateDeviceModel = updateDeviceModel;
  }

  async create(payload: any) {
    return await this.updateDeviceModel.create(payload);
  }

  async createMany?(payload: any) {
    return await this.updateDeviceModel.insertMany(payload);
  }

  async update(id: any, payload: UpdateDevicesDto) {
    return await this.updateDeviceModel.findOneAndUpdate({ _id: id }, payload, {
      new: true,
    });
  }

  async find(payload?: any, id?: any) {
    return await this.updateDeviceModel.find(payload);
  }

  async findAll(payload?: any) {}

  async findById(id?: any) {
    return await this.updateDeviceModel.findById(id);
  }

  async delete(id: any) {
    return await this.updateDeviceModel.deleteOne({ _id: id });
  }

  async count(payload: any) {
    return await this.updateDeviceModel.count(payload);
  }
}
