function [] = showNormImages( fName, iter )

addpath ../../external/tight_subplot

allImages = {};
minVals = [];
maxVals = [];

for iI=0:9
  
  currentFileName = sprintf( '%s%03d-iter-%03d.nrrd', fName, iI, iter );
  fprintf('Loading %s\n', currentFileName );
  cI = nrrdLoad( currentFileName );
  nI = ( cI(:,:,1).^2 + cI(:,:,2).^2 ).^0.5;
  allImages{iI+1} = nI;
  
  minVals = [minVals; min( allImages{iI+1}(:) ) ];
  maxVals = [maxVals; max( allImages{iI+1}(:) ) ];
  
end

figure

ha = tight_subplot(2,5,[.01 .01],[.01 .01],[.01 .01]);

for iI=0:9
  %subplot(2,5,iI+1 );
  subplot( ha( iI+1 ) );
  imagesc( allImages{iI+1}, [minVals( iI+1 ), maxVals( iI+1 ) ] )
  axis image
  xlabel( sprintf('%d: [%2.2f,%2.2f]', iI, minVals(iI+1), maxVals(iI+1) ) );
  colorbar
end

set( gcf, 'name', sprintf('%s -- iter = %d', fName, iter ) );