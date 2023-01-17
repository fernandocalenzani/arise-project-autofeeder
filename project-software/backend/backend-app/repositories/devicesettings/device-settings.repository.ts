import IRepository from '../IRepositiry';
import { Model } from 'mongoose';
import { IDeviceSettings } from '../../models/device-settings.model';
import { DeviceSettingsDto } from '../../modules/devicesettings/services/dtos/device-settings.dto';

export class DeviceSyncRepository implements IRepository {
  private devicesettingsModel: any;

  constructor(devicesettingsModel: Model<IDeviceSettings>) {
    this.devicesettingsModel = devicesettingsModel;
  }

  async create(payload: DeviceSettingsDto) {
    return await this.devicesettingsModel.create(payload);
  }

  async update(id: any, payload: DeviceSettingsDto) {
    return await this.devicesettingsModel.findOneAndUpdate(
      { _id: id },
      payload,
      {
        new: true,
      }
    );
  }

  async findAll() {
    return await this.devicesettingsModel.findAll();
  }

  async findById(id: any) {
    return await this.devicesettingsModel.findById(id);
  }

  async delete(id: any) {
    return await this.devicesettingsModel.delete({ _id: id });
  }

  async count(payload: any) {
    return await this.devicesettingsModel.count(payload);
  }

  async createMany?(payload: any) {
    throw new Error('Method not implemented.');
  }
  async find(payload?: any, id?: any) {
    throw new Error('Method not implemented.');
  }
}
