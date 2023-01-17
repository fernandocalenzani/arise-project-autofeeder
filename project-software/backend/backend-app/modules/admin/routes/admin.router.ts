import express from 'express';

const adminRouter = express.Router();

adminRouter.get('/admin/dashboard', (req, res) => {
  res.send('dashboard');
});

adminRouter.get('/admin/update/alldevices', (req, res) => {
  res.send('Update all devices');
});

adminRouter.get('/admin/update/onedevice/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

adminRouter.get('/admin/devices/manufactured', (req, res) => {
  res.send('devices manufactured');
});

adminRouter.post('/admin/devices/register', (req, res) => {
  res.send('devices registered');
});

adminRouter.post('/admin/update/alldevices', (req, res) => {
  res.send('update all devices');
});

adminRouter.post('/admin/update/onedevice/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

adminRouter.put('/admin/update/alldevices/:version', (req, res) => {
  const sn: number = +req.params.version;
  res.send(`update all device sn: ${sn}`);
});

adminRouter.put('/admin/devices/manufactured/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`put device manufactured sn: ${sn}`);
});

adminRouter.put('/admin/update/onedevice/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`put device manufactured sn: ${sn}`);
});

adminRouter.delete('/admin/update/alldevices/:version', (req, res) => {
  const sn: number = +req.params.version;
  res.send(`put device manufactured sn: ${sn}`);
});

adminRouter.delete('/admin/update/onedevice/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`put device manufactured sn: ${sn}`);
});

export default adminRouter;
