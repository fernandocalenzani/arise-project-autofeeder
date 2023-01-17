import { auth, requiresAuth } from 'express-openid-connect';
import { auth0Config } from './config';

export const auth0Auth = auth(auth0Config);
export const auth0MiddlewareAuth = requiresAuth();
