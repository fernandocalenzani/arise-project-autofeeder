import express from 'express';

const devicedataRouter = express.Router();

devicedataRouter.get('/devicedata/config/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`device configure sn: ${sn}`);
});

devicedataRouter.get('/devicedata/update/alldevices', (req, res) => {
  res.send(`device configure sn:`);
});

devicedataRouter.get(
  '/devicedata/update/onedevice/:serialNumber',
  (req, res) => {
    const sn: number = +req.params.serialNumber;
    res.send(`device configure sn: ${sn}`);
  }
);

devicedataRouter.post('/devicedata', (req, res) => {
  res.send(`my devices`);
});

devicedataRouter.post('/devicedata/alerts', (req, res) => {
  res.send(`my devices`);
});

devicedataRouter.put('/devicedata/config/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

export default devicedataRouter;
