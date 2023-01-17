import { Router } from 'express';
import userRouter from '../../modules/users/routes/user.router';

const routes = Router();

routes.use('/users', userRouter);

export default baseRoutes;

export { userRouter };
