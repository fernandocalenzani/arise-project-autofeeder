import express from 'express';

const devicesRouter = express.Router();

devicesRouter.get('/devices/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`device configure sn: ${sn}`);
});

devicesRouter.post('/devices', (req, res) => {
  res.send(`my devices`);
});

devicesRouter.delete('/devices/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

export default devicesRouter;
