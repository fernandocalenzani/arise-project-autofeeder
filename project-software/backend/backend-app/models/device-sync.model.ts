import { Schema, model } from 'mongoose';
import { IUser } from './user.model';

export interface IDeviceSync {
  serialNumber: string;
  user: Schema.Types.ObjectId | IUser;
}

const devicesyncSchema = new Schema<IDeviceSync>(
  {
    serialNumber: { type: String, required: true },
    user: { type: Schema.Types.ObjectId, ref: 'User' },
  },
  { timestamps: true }
);

export default model<IDeviceSync>('DeviceSync', devicesyncSchema);
