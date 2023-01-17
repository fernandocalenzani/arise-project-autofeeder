import { Schema, model } from 'mongoose';
import { IDeviceSync } from './device-sync.model';

export interface IDeviceAlerts {
  serialNumber: Schema.Types.ObjectId | IDeviceSync;
  alerts: string;
}

const devicealertsSchema = new Schema<IDeviceAlerts>(
  {
    serialNumber: { type: Schema.Types.ObjectId, ref: 'DeviceSync' },
    alerts: { type: String, required: true },
  },
  { timestamps: true }
);

export default model<IDeviceAlerts>('DeviceAlerts', devicealertsSchema);
