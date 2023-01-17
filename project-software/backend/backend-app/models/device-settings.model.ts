import { Schema, model } from 'mongoose';
import { IDeviceSync } from './device-sync.model';

export interface IDeviceSettings {
  serialNumber: Schema.Types.ObjectId | IDeviceSync;
  applications: string[];
  operation: boolean;
  gmt: number;
  ktm: number;
}

const devicesettingsSchema = new Schema<IDeviceSettings>(
  {
    serialNumber: { type: Schema.Types.ObjectId, ref: 'DeviceSync' },
    applications: [{ type: String, required: true }],
    operation: { type: Boolean, required: true },
    gmt: { type: Number, required: true },
    ktm: { type: Number, required: true },
  },
  { timestamps: true }
);

export default model<IDeviceSettings>('DeviceSettings', devicesettingsSchema);
