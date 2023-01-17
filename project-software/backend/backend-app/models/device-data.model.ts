import { Schema, model } from 'mongoose';
import { IDeviceSync } from './device-sync.model';

export interface IDeviceData {
  serialNumber: Schema.Types.ObjectId | IDeviceSync;
  temperature: number;
  umidity: number;
  tanklevel: number;
  productflow: number;
  totalproduct: number;
  hallfield: number;
  InternalTemperature: number;
  rssi: number;
}

const devicedataSchema = new Schema<IDeviceData>(
  {
    serialNumber: { type: Schema.Types.ObjectId, ref: 'DeviceSync' },
    temperature: { type: Number, required: true },
    umidity: { type: Number, required: true },
    tanklevel: { type: Number, required: true },
    productflow: { type: Number, required: true },
    totalproduct: { type: Number, required: true },
    hallfield: { type: Number, required: true },
    InternalTemperature: { type: Number, required: true },
    rssi: { type: Number, required: true },
  },
  { timestamps: true }
);

export default model<IDeviceData>('DeviceData', devicedataSchema);
