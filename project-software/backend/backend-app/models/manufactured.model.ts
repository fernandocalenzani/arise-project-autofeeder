import { Date, Schema, model } from 'mongoose';

export interface IManufactured {
  manufacturingDate: Date;
  model: string;
  serialNumber: string;
}

const manufacturedSchema = new Schema<IManufactured>(
  {
    manufacturingDate: { type: Date, required: true },
    model: { type: String, required: true },
    serialNumber: { type: String, required: true },
  },
  { timestamps: true }
);
export default model<IManufactured>('Manufactured', manufacturedSchema);
