import { Schema, model } from 'mongoose';
import USER_LEVEL from '../constants/user-level';

export interface IUser {
  name: string;
  email: string;
  password: string;
  level: number;
  country: string;
  city: string;
  stateFrom: string;
}

const userSchema = new Schema<IUser>(
  {
    name: { type: String, required: true },
    email: { type: String, required: true },
    password: { type: String, required: true },
    level: { type: Number, required: true, default: USER_LEVEL.USER },
    country: { type: String, required: true },
    city: { type: String, required: true },
    stateFrom: { type: String, required: true },
  },
  { timestamps: true }
);

export default model<IUser>('User', userSchema);
