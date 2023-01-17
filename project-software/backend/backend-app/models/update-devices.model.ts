import { Date, Schema, model } from 'mongoose';

export interface IUpdateDevices {
  timeUpdateFirmware: Date;
  newVersion: string;
  currentVersion: string;
  keyOTA: string;
  serialNumber: string;
}

const updatedevicesSchema = new Schema(
  {
    timeUpdateFirmware: { type: Date, required: true },
    newVersion: { type: String, required: true },
    currentVersion: { type: String, required: true },
    keyOTA: { type: String, required: true },
    serialNumber: { type: String, required: true },
  },
  {
    timestamps: true,
  }
);

export default model<IUpdateDevices>('UpdateDevices', updatedevicesSchema);
