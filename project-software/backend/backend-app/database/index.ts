import ENV from '../infra/config/env';
import DBConnection from './connection';

export const mongoDBConnection = new DBConnection(ENV.MONGO_URL);
