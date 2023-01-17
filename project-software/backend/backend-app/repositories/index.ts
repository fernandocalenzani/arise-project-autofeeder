import { updateDevicesModel, manufacturedModel, userModel } from '../models';
import { ManufacturedRepository } from './admin/manufactured.repository';
import { UpdateDevicesRepository } from './admin/update-devices.repository';
import { UserRepository } from './user/user.repository';

const manufacturedRepository = new ManufacturedRepository(manufacturedModel);
const updateDevicesRepository = new UpdateDevicesRepository(updateDevicesModel);
const userRepository = new UserRepository(userModel);

export { manufacturedRepository, updateDevicesRepository, userRepository };
