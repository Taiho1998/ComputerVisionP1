#pragma once
#ifndef NS3_HISTOGRAM_H
#define NS3_HISTOGRAM_H

 #include <vector>
 #include <stdint.h>
 #include <ostream>

 namespace ns3 {
	
		 class Histogram
		 {
		 public:
			
				   // --- basic methods ---
				   Histogram(double binWidth);
			   Histogram();
			
				   // Methods for Getting the Histogram Results
				   uint32_t GetNBins() const;
			   double GetBinStart(uint32_t index);
			   double GetBinEnd(uint32_t index);
			   double GetBinWidth(uint32_t index) const;
			   void SetDefaultBinWidth(double binWidth);
			   uint32_t GetBinCount(uint32_t index);
			
				   // Method for adding values
				   void AddValue(double value);
			
				   void SerializeToXmlStream(std::ostream & os, int indent, std::string elementName) const;
			
				
		 private:
			   std::vector<uint32_t> m_histogram;
			   double m_binWidth;
			 };
	
} // namespace ns3

#endif /* NS3_HISTOGRAM_H */
